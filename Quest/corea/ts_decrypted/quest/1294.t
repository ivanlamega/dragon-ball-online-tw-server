CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1294;
	title = 129402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 129409;
				ctype = 1;
				idx = 2611102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 129408;
				m1fx = "1811.000000";
				m2fz = "4265.000000";
				m1fy = "0.000000";
				sort = 129405;
				m2widx = 1;
				grade = 132203;
				m0fx = "2023.000000";
				m0ttip = 129415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 129402;
				gtype = 2;
				area = 129401;
				goal = 129404;
				m0fz = "3628.000000";
				m0widx = 1;
				m1ttip = 129415;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "4273.000000";
				m2fx = "2183.000000";
				m2ttip = 129415;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 5;
				idx0 = 178;
				cnt0 = 3;
				ectype = -1;
				etype = 0;
				qtidx = 129430;
				taid = 3;
				esctype = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
				itype = 5;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActItem
			{
				iidx0 = 99041;
				stype0 = 1;
				taid = 1;
				type = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActItem
			{
				iidx0 = 99041;
				stype0 = 1;
				taid = 2;
				type = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 5;
				idx0 = -1;
				cnt0 = 0;
				ectype = -1;
				etype = 1;
				qtidx = -1;
				taid = 1;
				esctype = 0;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 129407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2611102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 129408;
			gtype = 2;
			oklnk = 2;
			area = 129401;
			goal = 129404;
			sort = 129405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 129402;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 129414;
			nextlnk = 101;
			rwdtbl = 129401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2611102;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 253;
			prelnk = "0;";

			CDboTSActItem
			{
				iidx0 = 99041;
				stype0 = 1;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;";
			type = 0;
		}
	}
}

