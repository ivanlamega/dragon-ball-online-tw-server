#ifndef __PACKET_BUFFER_H_
#define __PACKET_BUFFER_H_

#include <vector>
#include <functional>
#include <Define.h>

#define DEFAULT_BUFFER_SIZE     4096

class PacketBuffer
{
	friend class Socket;

private:
	size_t m_writePosition;
	size_t m_readPosition;

	std::vector<uint8> m_buffer;

public:
	PacketBuffer(int initialSize = DEFAULT_BUFFER_SIZE);

	uint8 Peak() const { return m_buffer[m_readPosition]; }

	void Read(char *buffer, int length);
	size_t ReadLengthRemaining() const { return m_writePosition - m_readPosition; }

	void Write(const char *buffer, int length);
};

#endif /* !__PACKET_BUFFER_H_ */