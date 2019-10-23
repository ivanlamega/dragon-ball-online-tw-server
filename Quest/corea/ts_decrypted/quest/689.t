CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 689;
	title = 68902;

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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 68909;
				ctype = 1;
				idx = 3173101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 68908;
				m1fx = "6533.700195";
				area = 68901;
				goal = 68904;
				m0fz = "502.000000";
				m0widx = 1;
				m1fy = "-108.000000";
				m1ttip = 68916;
				sort = 68905;
				stype = 2;
				m0fy = "-108.000000";
				m1fz = "502.000000";
				grade = 132203;
				m0fx = "6533.700195";
				m0ttip = 68915;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 68902;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 0;
				idx0 = 1712101;
				cnt0 = 10;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 1713100;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 68908;
			gtype = 2;
			oklnk = 2;
			area = 68901;
			goal = 68904;
			sort = 68905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 68902;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 68914;
			nextlnk = 101;
			rwdtbl = 68901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3173101;
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
			stdiag = 68907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3173101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 31;
				minlvl = 23;
			}
			CDboTSCheckClrQst
			{
				and = "688;";
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

