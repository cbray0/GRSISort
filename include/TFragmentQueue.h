#ifndef TTIGFRAGMENTQUEUE_H
#define TTIGFRAGMENTQUEUE_H

#include <stdio.h>
#include <queue>
#include <map>

#ifndef __CINT__
#define _GLIBCXX_USE_NANOSLEEP 1
#include <thread>
#include <mutex>
#endif

#include<TObjArray.h>
#include<TStopwatch.h>

#include "TFragment.h"

class TFragmentQueue : public TObject {
	
	public:
		static TFragmentQueue *GetQueue(std::string quename = "GOOD");
		virtual ~TFragmentQueue();

      int FragsInQueue() { return fFragsInQueue;   }

	private:
		static TFragmentQueue *fFragmentQueueClassPointer;
      static std::map<std::string,TFragmentQueue*> *fFragmentMap;
      TFragmentQueue();
	

		std::queue<TFragment*> fFragmentQueue;
		int fFragsInQueue;

		void StatusUpdate();
		bool fStatusUpdateOn;

		bool fStop;
		
		int fragments_in;		
		int fragments_out;

		TStopwatch *sw;
		void ResetRateCounter();

		unsigned int fTotalFragsIn;
		unsigned int fTotalFragsOut;	

		std::map<int,int> fragment_id_map;	


#ifndef __CINT__
#ifndef NO_MUTEX
	public:
		static std::mutex All;
		static std::mutex Sorted;
#endif
#endif

	public:
		void Add(TFragment*);
		//void Add(TGrifFragment*);


		//TFragment *GetQueue();	
	
		void Pop();
		TFragment *PopFragment();

		int Size();

		void StartStatusUpdate();
		void StopStatusUpdate();
		void CheckStatus();

		unsigned int GetTotalFragsIn() { return fTotalFragsIn;}
		unsigned int GetTotalFragsOut()	{	return fTotalFragsOut;}

		bool Running() { return !fStop;}
		void Stop() { fStop = true;}

      void Print(Option_t *opt = "");
		void Clear(Option_t *opt = "");
		
		ClassDef(TFragmentQueue,0);
};






#endif
