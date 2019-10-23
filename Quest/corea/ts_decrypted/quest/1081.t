CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1081;
	title = 108102;

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
			cont = 108108;
			gtype = 5;
			oklnk = 2;
			area = 108101;
			goal = 108104;
			sort = 108105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 108102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 108114;
			nextlnk = 101;
			rwdtbl = 108101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1655101;
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
			stdiag = 108107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1655101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
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
				conv = 108109;
				ctype = 1;
				idx = 1655101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 108108;
				gtype = 5;
				area = 108101;
				goal = 108104;
				m0fz = "153.000000";
				m0widx = 4;
				sort = 108105;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "84.000000";
				m0ttip = 108115;
				rwd = 100;
				taid = 1;
				title = 108102;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 6413100;
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

