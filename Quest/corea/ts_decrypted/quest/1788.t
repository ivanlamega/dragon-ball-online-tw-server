CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1788;
	title = 178802;

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
			cont = 178808;
			gtype = 2;
			oklnk = 2;
			area = 178801;
			goal = 178804;
			sort = 178805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 178802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 178814;
			nextlnk = 101;
			rwdtbl = 178801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7131124;
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
			stdiag = 178807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7131124;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
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
				conv = 178809;
				ctype = 1;
				idx = 7131124;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 178808;
				gtype = 2;
				area = 178801;
				goal = 178804;
				m0fz = "1348.000000";
				m0widx = 1;
				sort = 178805;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "-2202.000000";
				m0ttip = 178815;
				rwd = 100;
				taid = 1;
				title = 178802;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 6811201;
				cnt0 = 15;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
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
				itype = 0;
			}
		}
	}
}

