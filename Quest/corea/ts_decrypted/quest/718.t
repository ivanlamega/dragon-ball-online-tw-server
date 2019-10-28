CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 718;
	title = 71802;

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
				eitype = 3;
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
			cid = 9;
			elnk = 255;
			nextlnk = 100;
			prelnk = "8;";

			CDboTSActMiniNarration
			{
				taid = 1;
				tidx = 7182;
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
			stdiag = 71807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1551105;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 32;
				minlvl = 24;
			}
			CDboTSCheckClrQst
			{
				and = "717;";
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 71814;
			nextlnk = 101;
			rwdtbl = 71801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "9;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1551105;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 1;
				iidx = 688;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 8;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 71809;
				ctype = 1;
				idx = 1551105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 71808;
				gtype = 3;
				area = 71801;
				goal = 71804;
				m0fz = "-51.000000";
				m0widx = 1;
				sort = 71805;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "7043.000000";
				m0ttip = 71815;
				rwd = 100;
				taid = 1;
				title = 71802;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 688;
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
			cont = 71808;
			gtype = 3;
			oklnk = 2;
			area = 71801;
			goal = 71804;
			sort = 71805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 71802;
		}
		CDboTSContGCond
		{
			cid = 8;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 9;

			CDboTSCheckSToCEvt
			{
				itype = 3;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 71807;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 688;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 688;
				taid = 1;
				type = 1;
			}
		}
	}
}

