#ifndef _ENCRYPT_H
#define _ENCRYPT_H

#pragma once

#include <Logger.h>
#include <Packet.h>

class RandomGen
{
public:
	RandomGen(void) {};
	RandomGen(unsigned int seed);
	RandomGen& operator=(RandomGen & rRandGen);
	virtual ~RandomGen(void) {};
public:
	unsigned int Generate();
	void Reset();
protected:
	enum { TABLE_SIZE = 250 };
	void Init(unsigned int seed);
	void GenerateSeeds();
	unsigned int GenerateSimple();
private:
	unsigned int m_nState;
	int m_nIndex1;
	int m_nIndex2;
	unsigned int m_seed;
	unsigned int m_table[TABLE_SIZE];
};

class PacketEncoder
{
public:
	PacketEncoder(bool bSeedSwap = false);
	~PacketEncoder(void) {};
	int RxDecrypt(void * pvPacketHeader);
	int TxEncrypt(void * pvPacketHeader);
	int RxDecrypt(Packet& rPacket);
	int TxEncrypt(Packet& rPacket);
private:
	RandomGen m_rxBodyKeyGenerator;
	RandomGen m_txBodyKeyGenerator;
	RandomGen m_rxHeaderKeyGenerator;
	RandomGen m_txHeaderKeyGenerator;
};

#endif