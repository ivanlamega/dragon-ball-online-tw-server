CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 609;
	title = 60902;

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
				eitype = 1;
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
			stdiag = 60907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031205;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 60914;
			nextlnk = 101;
			rwdtbl = 60901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031205;
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
				conv = 60909;
				ctype = 1;
				idx = 3031205;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 60908;
				m1fx = "6457.000000";
				m2fz = "2127.000000";
				m1fy = "0.000000";
				sort = 60905;
				m2widx = 1;
				grade = 132203;
				m0fx = "6779.000000";
				m0ttip = 60915;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 60902;
				gtype = 2;
				area = 60901;
				goal = 60904;
				m0fz = "2227.000000";
				m0widx = 1;
				m1ttip = 60916;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "2283.000000";
				m2fx = "6735.000000";
				m2ttip = 60917;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 9;
				eitype = 1;
				idx0 = 522;
				cnt0 = 9;
				cnt2 = 9;
				ectype = -1;
				etype = 0;
				idx1 = 523;
				taid = 3;
				esctype = 0;
				idx2 = 524;
			}
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
				itype = 1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 60908;
			gtype = 2;
			oklnk = 2;
			area = 60901;
			goal = 60904;
			sort = 60905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 60902;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 60907;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt2 = 255;
				iprob2 = "1.000000";
				icnt1 = 255;
				iidx0 = 522;
				iidx2 = 524;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
				icnt0 = 255;
				iidx1 = 523;
				iprob0 = "1.000000";
			}
		}
	}
}

