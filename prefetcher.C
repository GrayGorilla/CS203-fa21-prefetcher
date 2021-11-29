#include "prefetcher.h"
#include "mem-sim.h"

Prefetcher::Prefetcher() { isReady = false; }

bool Prefetcher::hasRequest(u_int32_t cycle) { return false; }

Request Prefetcher::getRequest(u_int32_t cycle) {
	Request req;
	req.addr = nextReqAddr;
	return req;
}

void Prefetcher::completeRequest(u_int32_t cycle) { isReady = false; }

void Prefetcher::cpuRequest(Request req) {
	if (!isReady) {
		nextReqAddr = req.addr + 16;
		isReady = true;
	}
}
