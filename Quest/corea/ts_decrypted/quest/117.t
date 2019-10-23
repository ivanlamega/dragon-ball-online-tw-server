CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 117;
	title = 11702;

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
				npcidx = 3331101;
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
				npcidx = 3331101;
			}
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
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckSToCEvt
			{
				itype = 3;
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
				conv = 11709;
				ctype = 1;
				idx = 3331101;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cd0 = 92001;
				cnt1 = 0;
				eitype = 3;
				idx0 = 283;
				cnt0 = 1;
				ectype = 0;
				esctype = 0;
				idx2 = -1;
				cnt2 = 0;
				etype = 0;
				idx1 = -1;
				taid = 3;
			}
			CDboTSActRegQInfo
			{
				cont = 11708;
				gtype = 1;
				area = 11701;
				goal = 11704;
				m0fz = "4365.000000";
				m0widx = 1;
				sort = 11705;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "4838.000000";
				m0ttip = 11715;
				rwd = 100;
				taid = 1;
				title = 11702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 11707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 24;
				minlvl = 16;
			}
			CDboTSClickNPC
			{
				npcidx = 3331101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckPCCls
			{
				clsflg = 3;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 11708;
			gtype = 1;
			oklnk = 2;
			area = 11701;
			goal = 11704;
			sort = 11705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 11702;
		}
		CDboTSContReward
		{
			canclnk = 101;
			cid = 100;
			desc = 11714;
			nextlnk = 254;
			rwdtbl = 11701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;101;";
			usetbl = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
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
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;1;";
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
				iidx = 283;
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
				iidx0 = 283;
				taid = 1;
				type = 1;
			}
		}
	}
}

