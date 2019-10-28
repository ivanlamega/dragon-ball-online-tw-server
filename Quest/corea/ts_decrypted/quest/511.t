CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 511;
	title = 51102;

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
				eitype = 1;
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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 51107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5063101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 24;
				minlvl = 16;
			}
			CDboTSCheckClrQst
			{
				and = "510;";
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
				conv = 51109;
				ctype = 1;
				idx = 5063101;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 6;
				eitype = 1;
				idx0 = 657;
				cnt0 = 6;
				cnt2 = 6;
				ectype = -1;
				etype = 0;
				idx1 = 658;
				taid = 3;
				esctype = 0;
				idx2 = 659;
			}
			CDboTSActRegQInfo
			{
				cont = 51108;
				m1fx = "6626.000000";
				m2fz = "-2152.000000";
				m1fy = "0.000000";
				sort = 51105;
				m2widx = 1;
				grade = 132203;
				m0fx = "6591.000000";
				m0ttip = 51115;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 51102;
				gtype = 2;
				area = 51101;
				goal = 51104;
				m0fz = "-1770.000000";
				m0widx = 1;
				m1ttip = 51116;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-1706.000000";
				m2fx = "6769.000000";
				m2ttip = 51117;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 51114;
			nextlnk = 101;
			rwdtbl = 51101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5063101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 51108;
			gtype = 2;
			oklnk = 2;
			area = 51101;
			goal = 51104;
			sort = 51105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 51102;
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
				itype = 1;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 254;
			prelnk = "4;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 659;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "6;3;";
			nolnk = 254;
			rm = 0;
			yeslnk = 5;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 659;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;1;";
			nolnk = 4;
			rm = 0;
			yeslnk = 6;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 658;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 657;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 6;
			elnk = 255;
			nextlnk = 4;
			prelnk = "3;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 658;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 3;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 657;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "5;4;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

