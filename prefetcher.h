#ifndef PREFETCHER_H
#define PREFETCHER_H

#include <sys/types.h>
#include <unordered_set>

struct Request;

class Prefetcher {
	private:
	static const u_int32_t MASK = 0xFFFF8000;		// First 17 bits to get tag
	// static const u_int32_t MASK_B = 0b11111111111111111000000000000000;
	bool isReady;
	u_int32_t nextReqAddr;
	std::unordered_set<u_int32_t> tags;

  public:
	Prefetcher();

	// should return true if a request is ready for this cycle
	bool hasRequest(u_int32_t cycle);

	// request a desired address be brought in
	Request getRequest(u_int32_t cycle);

	// this function is called whenever the last prefetcher request was successfully sent to the L2
	void completeRequest(u_int32_t cycle);

	/*
	 * This function is called whenever the CPU references memory.
	 * Note that only the addr, pc, load, issuedAt, and HitL1 should be considered valid data
	 */
	void cpuRequest(Request req); 
};

#endif
