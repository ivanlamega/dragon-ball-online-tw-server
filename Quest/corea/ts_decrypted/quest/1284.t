CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1284;
	title = 128402;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 128407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1551107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
			CDboTSCheckClrQst
			{
				and = "1281;1282;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 128408;
				gtype = 2;
				area = 128401;
				goal = 128404;
				m0fz = "3890.000000";
				m0widx = 1;
				sort = 128405;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "1963.000000";
				m0ttip = 128415;
				rwd = 100;
				taid = 1;
				title = 128402;
			}
			CDboTSActNPCConv
			{
				conv = 128409;
				ctype = 1;
				idx = 1551107;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 7112308;
				cnt0 = 26;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 128414;
			nextlnk = 101;
			rwdtbl = 128401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1551107;
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
			cont = 128408;
			gtype = 2;
			oklnk = 2;
			area = 128401;
			goal = 128404;
			sort = 128405;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 128402;
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

