CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 279;
	title = 27902;

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
				cnt1 = 1;
				eitype = 0;
				idx0 = 2313101;
				cnt0 = 13;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = 2312106;
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
			stdiag = 27907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511202;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 21;
				minlvl = 13;
			}
			CDboTSCheckClrQst
			{
				and = "269;";
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
				conv = 27909;
				ctype = 1;
				idx = 4511202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 27908;
				m1fx = "4878.000000";
				area = 27901;
				goal = 27904;
				m0fz = "-2804.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 27916;
				sort = 27905;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-2715.000000";
				grade = 132203;
				m0fx = "5049.000000";
				m0ttip = 27915;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 27902;
				gtype = 3;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 0;
				idx0 = 2313101;
				cnt0 = 8;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 2312106;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 27914;
			nextlnk = 101;
			rwdtbl = 27901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511202;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 27908;
			gtype = 3;
			oklnk = 2;
			area = 27901;
			goal = 27904;
			sort = 27905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 27902;
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

