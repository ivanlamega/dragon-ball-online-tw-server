CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 294;
	title = 29402;

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
				cnt1 = 1;
				eitype = 0;
				idx0 = 3212101;
				cnt0 = 20;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = 3212107;
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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 29407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4751102;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 22;
				minlvl = 14;
			}
			CDboTSCheckClrQst
			{
				and = "287;";
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
				cont = 29408;
				m1fx = "4722.000000";
				area = 29401;
				goal = 29404;
				m0fz = "-2513.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 29416;
				sort = 29405;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-2233.000000";
				grade = 132203;
				m0fx = "4693.000000";
				m0ttip = 29415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 29402;
				gtype = 3;
			}
			CDboTSActNPCConv
			{
				conv = 29409;
				ctype = 1;
				idx = 4751102;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 0;
				idx0 = 3212101;
				cnt0 = 15;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 3212107;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 29414;
			nextlnk = 101;
			rwdtbl = 29401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 29408;
			gtype = 3;
			oklnk = 2;
			area = 29401;
			goal = 29404;
			sort = 29405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 29402;
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

