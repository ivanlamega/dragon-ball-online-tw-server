CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 684;
	title = 68402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 68407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 1351211;
			}
			CDboTSCheckLvl
			{
				maxlvl = 31;
				minlvl = 23;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 68414;
			nextlnk = 101;
			rwdtbl = 68401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1351211;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 68409;
				ctype = 1;
				idx = 1351211;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 68408;
				m1fx = "5295.500000";
				area = 68401;
				goal = 68404;
				m0fz = "198.199997";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 68416;
				sort = 68405;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-94.559998";
				grade = 132203;
				m0fx = "5029.700195";
				m0ttip = 68415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 68402;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 12;
				eitype = 0;
				idx0 = 1712101;
				cnt0 = 12;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 1712102;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 68408;
			gtype = 2;
			oklnk = 2;
			area = 68401;
			goal = 68404;
			sort = 68405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 68402;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

