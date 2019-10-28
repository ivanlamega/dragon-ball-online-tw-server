CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1814;
	title = 181402;

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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 181407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5591205;
			}
			CDboTSCheckLvl
			{
				maxlvl = 41;
				minlvl = 33;
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
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 181409;
				ctype = 1;
				idx = 5591205;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 181408;
				gtype = 2;
				area = 181401;
				goal = 181404;
				m0fz = "-84.000000";
				m0widx = 1;
				sort = 181405;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3744.000000";
				m0ttip = 181415;
				rwd = 100;
				taid = 1;
				title = 181402;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 5812200;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 181408;
			gtype = 2;
			oklnk = 2;
			area = 181401;
			goal = 181404;
			sort = 181405;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 181402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 181414;
			nextlnk = 101;
			rwdtbl = 181401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5591205;
			}
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
			prelnk = "252;0;1;";
			type = 0;
		}
	}
}

