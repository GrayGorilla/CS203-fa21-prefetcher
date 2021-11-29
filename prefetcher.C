#include "prefetcher.h"
#include "mem-sim.h"
#include <iostream>

Prefetcher::Prefetcher() { isReady = false; }

bool Prefetcher::hasRequest(u_int32_t cycle) { return isReady; }

Request Prefetcher::getRequest(u_int32_t cycle) {
	Request req;
	req.addr = nextReqAddr;
	return req;
}

void Prefetcher::completeRequest(u_int32_t cycle) { isReady = false; }

void Prefetcher::cpuRequest(Request req) {
	
	u_int32_t tag, newStride;
	rptEntry entry;
	std::map<u_int32_t, rptEntry>::iterator it;

	tag = req.addr & MASK;
	it = rpt.find(tag);

	// New Tag
	if (it == rpt.end()) {
		entry.prevAddr = req.addr;
		entry.state = INITIAL;
		rpt.insert(std::pair<u_int32_t, rptEntry>(tag, entry));
	// Existing Tag
	} else {
		entry = it->second;
		newStride = req.addr - entry.prevAddr;

		switch (entry.state) {
			case INITIAL:
				entry.state = TRANSIENT;
				break;
			case TRANSIENT:
				if (newStride == entry.stride) {
					entry.state = STEADY;
				} else {
					entry.state = NO_PRED;
				}
				break;
			case STEADY:
				if (newStride != entry.stride) {
					entry.state = INITIAL;
				}
				break;
			case NO_PRED:
				if (newStride == entry.stride) {
					entry.state = TRANSIENT;
				}
				break;
			default:
				std::cerr << "Error: Controller should not reach this point" << std::endl;
				break;
		}
		entry.prevAddr = req.addr;
		entry.stride = newStride;
		it->second = entry;
	}

	// =======================================================================================
	// printf("Request Address: %x\n", req.addr);
	// std::cout << "Request Address: " << std::hex << req.addr << std::endl;
	if (!isReady && entry.state == STEADY) {
		nextReqAddr = req.addr + entry.stride;
		isReady = true;
	}
}
