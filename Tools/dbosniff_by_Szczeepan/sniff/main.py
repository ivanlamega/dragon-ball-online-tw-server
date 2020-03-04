import os
from collections import OrderedDict
import dpkt
import struct
import hashlib
import enum_parser

log = ""
log_counter = 1
handles = {}

int2ip = \
    lambda n: '.'.join([str(n >> (i << 3) & 0xFF) for i in range(0, 4)[::-1]])

def append_log(opcode_name, length, h):
    global log_counter
    file = open('log.txt', 'a')
    file.write("%d. OPCODE: %s, LENGTH: %d, sha1: %s\n" % (log_counter, opcode_name, length, h))
    file.close()
   # print("%d. OPCODE: %s, LENGTH: %d, sha1: %s" % (log_counter, opcode_name, length, h))
    log_counter += 1

def map_opcode_to_name(enums, opcode):
    if opcode in enums:
        return enums[opcode]
    else:
        return opcode


def hash(data):
    hash_object = hashlib.sha1(data)
    return hash_object.hexdigest()

def chunker(seq, size):
    return (seq[pos:pos + size] for pos in range(0, len(seq), size))

def wstring2string(bytes):
    output = ""
    for wchar in chunker(bytes, 2):
        if wchar == b'\x00\x00':
            return output
        output += wchar.decode('utf-16')

def get_name(opcode, data, h):
    global handles
    global log_counter
    if opcode == "GU_OBJECT_CREATE":
        type = struct.unpack("B", data[8:9])[0]
        handle = struct.unpack("I", data[4:8])[0]
        if type == 0:
            nick_raw = data[18:52]
            nick = wstring2string(nick_raw)
            handles[handle] = [nick, 1]
            return ["{0}_{1}".format(nick, handle), "{0}_{1}_{2}_{3}.bin".format(1, opcode, type, h)]
        else:
            return ["", "{0}_{1}_{2}_{3}.bin".format(log_counter, opcode, type, h)]
    if opcode == "GU_TS_CONFIRM_STEP_RES":
        quest = struct.unpack("H", data[7:9])[0]
        return ["", "{0}_{1}_{2}_{3}.bin".format(log_counter, opcode, quest, h)]

    if(len(data) > 9):
        handle = struct.unpack("I", data[4:8])[0]
        if handle in handles:
            nick = handles[handle]
            i = handles[handle][1] + 1
            handles[handle][1] = i
            return ["{0}_{1}".format(nick[0], handle), "{0}_{1}_{2}.bin".format(i, opcode, h)]

    return ['',"{0}_{1}_{2}.bin".format(log_counter, opcode, h)]


def write_packet(opcode, data, h):
    t = get_name(opcode, data, h)
    path = "packets/{0}/{1}".format(t[0], t[1])
    os.makedirs("packets/" + t[0], exist_ok=True)
    file = open(path, 'wb')
    file.write(data)
    file.close()

filename = "tlq3.pcap"
ignore = []
find = []
#find = ['GU_TS_CONFIRM_STEP_RES']
ports = []
# ports = []

file = open(filename, 'rb')
pcap = dpkt.pcap.Reader(file)

enums = enum_parser.Enum_parser().get_names()


def parse_packet(packet):
    tcp_len = len(packet)
    if (len(packet) > 1):
        length = struct.unpack("H", packet[0:2])[0]
        opcode = struct.unpack("H", packet[2:4])[0]
        if ((length + 2) == tcp_len):
            opcode_name = map_opcode_to_name(enums, opcode)
            h = hash(packet)
            if (
                            (find and opcode_name in find) or
                            (ignore and opcode_name not in ignore) or
                        (not find and not ignore)
            ):
                write_packet(opcode_name, packet, h)
                append_log(opcode_name, length, h)
        else:
            print("encrypted packet: " + ' '.join(format(x, '02x') for x in packet))


def process_buffer(packet_list):
    packets = []
    packetstream = b''
    for packet in OrderedDict(
            sorted(packet_list.items(), key=lambda t: t[0])).values():
        packetstream += packet

    i = 0
    while len(packetstream) > 2:
        size = struct.unpack("H", packetstream[0:2])[0] + 2
        packet = packetstream[0:size]
        packetstream = packetstream[size:]
        if (size == 2):
            continue
        packets.append(packet)
        i += 1

    for packet in packets:
        if (len(packet) > 4):
            parse_packet(packet)


prev_seq = -1
prev_ack = -1
i = 0
packet_list = {}
for ts, buf in pcap:
    if buf[
        0] == 0x45:  # pcap zawiera jedynie pakiet ip, bez naglowka ethernetu, doklejamy losowe bajty dla kompatybilnosci
        eth_header = b'\x8c\x10\xd4\xba\x1e\xafL4\x88H\xba\xc0\x08\x00'
        buf = eth_header + buf

    eth = dpkt.ethernet.Ethernet(buf)
    src_ip = int2ip(struct.unpack("!I", eth.data.src)[0])
    ip = eth.data
    tcp = ip.data
    src_port = tcp.sport
    length = len(tcp.data)
    seq = tcp.seq
    ack = tcp.ack
    if (src_port in ports or not ports):
        if (ack != prev_ack):
            process_buffer(packet_list)
            packet_list = {}
        prev_ack = ack
        if length == 0:
            continue

        packet_list[seq] = tcp.data
        i += 1
        # print(i)
