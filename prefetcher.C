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
	
	u_int32_t tag = req.addr & MASK;
	std::unordered_set<u_int32_t>::iterator it = tags.find(tag);

	// New Tag
	if (it == tags.end()) {
		tags.insert(tag);
	// Existing Tag
	} else if (!isReady) {
		nextReqAddr = req.addr + 16;
		isReady = true;
	}
}
