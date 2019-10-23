CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 236;
	title = 23602;

	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
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
				iidx0 = 467;
				taid = 1;
				type = 1;
			}
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
				iidx = 467;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 0;

		CDboTSContUnifiedNarration
		{
			cancellnk = 100;
			cid = 5;
			idx = 2363;
			lilnk = 255;
			oklnk = 100;
			prelnk = "4;";
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "100;3;";
			nolnk = 255;
			rm = 1;
			yeslnk = 5;

			CDboTSClickNPC
			{
				npcidx = 4651102;
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
			stdiag = 23607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4651102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 15;
				minlvl = 7;
			}
			CDboTSCheckClrQst
			{
				or = "230;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 23608;
			gtype = 3;
			oklnk = 2;
			area = 23601;
			goal = 23604;
			sort = 23605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 23602;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 23609;
				ctype = 1;
				idx = 4651102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 23608;
				gtype = 3;
				area = 23601;
				goal = 23604;
				m0fz = "-2645.000000";
				m0widx = 1;
				sort = 23605;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3986.000000";
				m0ttip = 23615;
				rwd = 100;
				taid = 1;
				title = 23602;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 467;
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
		CDboTSContReward
		{
			canclnk = 4;
			cid = 100;
			desc = 23614;
			nextlnk = 101;
			rwdtbl = 23601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;5;";
			usetbl = 1;
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
				itype = 1;
			}
		}
	}
}

