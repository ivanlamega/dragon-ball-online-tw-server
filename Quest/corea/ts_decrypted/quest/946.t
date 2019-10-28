CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 946;
	title = 94602;

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
			stdiag = 94607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3172103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 42;
				minlvl = 34;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 94614;
			nextlnk = 101;
			rwdtbl = 94601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3172103;
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
				conv = 94609;
				ctype = 1;
				idx = 3172103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 94608;
				gtype = 2;
				area = 94601;
				goal = 94604;
				m0fz = "-275.000000";
				m0widx = 1;
				sort = 94605;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3741.000000";
				m0ttip = 94615;
				rwd = 100;
				taid = 1;
				title = 94602;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 1513104;
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
			cid = 1;
			cont = 94608;
			gtype = 2;
			oklnk = 2;
			area = 94601;
			goal = 94604;
			sort = 94605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 94602;
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

