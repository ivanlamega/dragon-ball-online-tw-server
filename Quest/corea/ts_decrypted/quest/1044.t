CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1044;
	title = 104402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 101;
			prelnk = "100;";
			nolnk = 255;
			rm = 1;
			yeslnk = 100;

			CDboTSClickNPC
			{
				npcidx = 6412105;
			}
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 5;

			CDboTSClickNPC
			{
				npcidx = 6412105;
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
			prelnk = "100;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 104407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 47;
				minlvl = 39;
			}
			CDboTSCheckClrQst
			{
				and = "1043;";
			}
			CDboTSClickNPC
			{
				npcidx = 1431101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContReward
		{
			canclnk = 101;
			cid = 100;
			desc = 104414;
			nextlnk = 254;
			rwdtbl = 104401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "101;5;";
			usetbl = 1;
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 100;
			prelnk = "4;";

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
			cont = 104408;
			gtype = 4;
			oklnk = 2;
			area = 104401;
			goal = 104404;
			sort = 104405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 104402;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 104409;
				ctype = 1;
				idx = 1431101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 104408;
				m1fx = "700.000000";
				area = 104401;
				goal = 104404;
				m0fz = "1000.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 104416;
				sort = 104405;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "964.000000";
				grade = 132203;
				m0fx = "742.000000";
				m0ttip = 104415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 104402;
				gtype = 4;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cd0 = 92026;
				cnt1 = 4;
				eitype = 0;
				idx0 = 7711100;
				cnt0 = 1;
				ectype = 0;
				esctype = 0;
				idx2 = -1;
				cnt2 = 0;
				etype = 0;
				idx1 = 6612206;
				taid = 3;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

