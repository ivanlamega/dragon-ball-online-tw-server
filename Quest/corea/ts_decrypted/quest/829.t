CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 829;
	title = 82902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "3;";
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
			prelnk = "0;252;2;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 82907;
			nolnk = 253;
			rm = 0;
			yeslnk = 2;

			CDboTSClickNPC
			{
				npcidx = 1653108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 36;
				minlvl = 28;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 82914;
			nextlnk = 101;
			rwdtbl = 82901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1653108;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 252;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActNPCConv
			{
				conv = 82909;
				ctype = 1;
				idx = 1653108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 82908;
				m1fx = "440.000000";
				area = 82901;
				goal = 82904;
				m0fz = "1565.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 82916;
				sort = 82905;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "448.000000";
				grade = 132203;
				m0fx = "7453.000000";
				m0ttip = 82915;
				m1widx = 3;
				rwd = 100;
				taid = 1;
				title = 82902;
				gtype = 3;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 2132102;
				cnt0 = 25;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
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
			cid = 2;
			cont = 82908;
			gtype = 3;
			oklnk = 3;
			area = 82901;
			goal = 82904;
			sort = 82905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 82902;
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
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

