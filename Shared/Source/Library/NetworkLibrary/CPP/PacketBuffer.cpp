#include "PacketBuffer.h"
#include <cassert>
#include <vector>
#include <cstring>

PacketBuffer::PacketBuffer(int initialSize) : m_writePosition(0), m_readPosition(0), m_buffer(initialSize, 0) {}

void PacketBuffer::Read(char *buffer, int length)
{
	assert(ReadLengthRemaining() >= length);

	if (!!buffer)
		memcpy(buffer, &m_buffer[m_readPosition], length);

	m_readPosition += length;
}

void PacketBuffer::Write(const char *buffer, int length)
{
	assert(!!buffer && !!length);

	const size_t newLength = m_writePosition + length;

	if (m_buffer.size() < newLength)
		m_buffer.resize(newLength);

	memcpy(&m_buffer[m_writePosition], buffer, length);

	m_writePosition += length;
}