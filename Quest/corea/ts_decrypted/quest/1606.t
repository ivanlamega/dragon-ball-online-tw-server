CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1606;
	title = 160602;

	CNtlTSGroup
	{
		gid = 0;

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
			stdiag = 160607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7073102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 160614;
			nextlnk = 101;
			rwdtbl = 160601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7073102;
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
				conv = 160609;
				ctype = 1;
				idx = 7073102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 160608;
				m1fx = "-2275.000000";
				m2fz = "353.000000";
				m1fy = "0.000000";
				sort = 160605;
				m2widx = 1;
				grade = 132203;
				m0fx = "-2250.000000";
				m0ttip = 160615;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 160602;
				gtype = 2;
				area = 160601;
				goal = 160604;
				m0fz = "480.000000";
				m0widx = 1;
				m1ttip = 160616;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "485.000000";
				m2fx = "-1998.000000";
				m2ttip = 160617;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 11;
				eitype = 0;
				idx0 = 8314100;
				cnt0 = 11;
				cnt2 = 11;
				ectype = -1;
				etype = 0;
				idx1 = 8315100;
				taid = 3;
				esctype = 0;
				idx2 = 8316100;
			}
		}
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 160608;
			gtype = 2;
			oklnk = 2;
			area = 160601;
			goal = 160604;
			sort = 160605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 160602;
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

