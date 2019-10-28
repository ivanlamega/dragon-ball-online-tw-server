CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1054;
	title = 105402;

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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 105407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4071114;
			}
			CDboTSCheckLvl
			{
				maxlvl = 48;
				minlvl = 40;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 105408;
			gtype = 4;
			oklnk = 2;
			area = 105401;
			goal = 105404;
			sort = 105405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 105402;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 105409;
				ctype = 1;
				idx = 4071114;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 105408;
				m1fx = "2054.000000";
				area = 105401;
				goal = 105404;
				m0fz = "1671.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 105416;
				sort = 105405;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "1728.000000";
				grade = 132203;
				m0fx = "2139.000000";
				m0ttip = 105415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 105402;
				gtype = 4;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 4;
				eitype = 0;
				idx0 = 1514100;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 4513111;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 105414;
			nextlnk = 101;
			rwdtbl = 105401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4071114;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
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

