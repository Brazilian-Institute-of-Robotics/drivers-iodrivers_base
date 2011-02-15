#include <iodrivers_base.hh>
#include <list>
#include <inttypes.h>

class IOParser{
public:
	virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const = 0;
};

class IOBusHandler : public IOParser{
public:
	virtual void packedReady(uint8_t const* buffer, size_t size)=0;
};

class IOBus : public IODriver{
public:
	IOBus(int max_packet_size, bool extract_last = false);
	int readPacket(uint8_t* buffer, int buffer_size, int packet_timeout, int first_byte_timeout, IOParser *parser=0);
	void addParser(IOParser *parser);
	void removeParser(IOParser *parser);
	int extractPacket(uint8_t const* buffer, size_t buffer_size) const;
protected:
	std::list<IOParser*> parser;
	IOParser *caller;
};

