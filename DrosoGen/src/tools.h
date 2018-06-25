#ifndef TOOLS_H
#define TOOLS_H


/// a datatype for keeping records of tracks
struct TrackRecord
{
	int ID;
	int fromTimeStamp;
	int toTimeStamp;
	int parentID;

	TrackRecord(int id, int from, int to, int pid):
		ID(id), fromTimeStamp(from), toTimeStamp(to), parentID(pid) {};

	TrackRecord():
		ID(0), fromTimeStamp(0), toTimeStamp(0), parentID(0) {};

	/** MoID mother got divided into DoAID and DoBID daughters
	    who came to being at frameNo, mother was last seen at frameNo-1;

	    it is also assumed that mother's track record is already existing */
	static 
	void ReportNewBornDaughters(std::map<int,TrackRecord>& tracks,
		const int MoID,
		const int DoAID, const int DoBID,
		const int frameNo)
	{
		//close the mother tracks
		tracks[MoID].toTimeStamp=frameNo-1;

		//start up two new daughter tracks
		tracks[DoAID].fromTimeStamp=frameNo;
		tracks[DoAID].toTimeStamp=-1;
		tracks[DoAID].parentID=MoID;

		tracks[DoBID].fromTimeStamp=frameNo;
		tracks[DoBID].toTimeStamp=-1;
		tracks[DoBID].parentID=MoID;
	}
};


/// helper macro to unify reports:
#define REPORT(x)        std::cout << __FUNCTION__ << "(): " << x << std::endl;
#define REPORT_NOENDL(x) std::cout << __FUNCTION__ << "(): " << x;

#ifdef DEBUG
	#define DEBUG_REPORT(x)         REPORT(x)
	#define DEBUG_REPORT_NOENDL(x)  REPORT_NOENDL(x)
#else
	#define DEBUG_REPORT(x)
	#define DEBUG_REPORT_NOENDL(x)
#endif

#endif
