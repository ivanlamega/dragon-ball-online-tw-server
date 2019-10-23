CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 866;
	title = 86602;

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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 86608;
			gtype = 4;
			oklnk = 2;
			area = 86601;
			goal = 86604;
			sort = 86605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 86602;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 86614;
			nextlnk = 101;
			rwdtbl = 86601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3173201;
			}
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
			stdiag = 86607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1653105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 38;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "865;";
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
				conv = 86609;
				ctype = 1;
				idx = 1653105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 86608;
				gtype = 4;
				area = 86601;
				goal = 86604;
				m0fz = "-321.000000";
				m0widx = 3;
				sort = 86605;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "355.000000";
				m0ttip = 86615;
				rwd = 100;
				taid = 1;
				title = 86602;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 4551100;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
	}
}

