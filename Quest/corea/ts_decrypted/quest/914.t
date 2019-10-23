CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 914;
	title = 91402;

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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 91409;
				ctype = 1;
				idx = 5061107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 91408;
				gtype = 3;
				area = 91401;
				goal = 91404;
				m0fz = "493.000000";
				m0widx = 1;
				sort = 91405;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3815.000000";
				m0ttip = 91415;
				rwd = 100;
				taid = 1;
				title = 91402;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 6611105;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 91408;
			gtype = 3;
			oklnk = 2;
			area = 91401;
			goal = 91404;
			sort = 91405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 91402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 91414;
			nextlnk = 101;
			rwdtbl = 91401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061107;
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
			stdiag = 91407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5061107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 39;
				minlvl = 31;
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

