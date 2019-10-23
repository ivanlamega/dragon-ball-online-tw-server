CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 668;
	title = 66802;

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
				npcidx = 4141101;
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
				npcidx = 4141101;
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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 66807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4141101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
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
				conv = 66809;
				ctype = 1;
				idx = 4141101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 66808;
				m1fx = "5475.000000";
				area = 66801;
				goal = 66804;
				m0fz = "698.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 66816;
				sort = 66805;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "832.000000";
				grade = 132203;
				m0fx = "6308.000000";
				m0ttip = 66815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 66802;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cd0 = 92024;
				cnt1 = 9;
				eitype = 1;
				idx0 = 684;
				cnt0 = 9;
				ectype = 0;
				esctype = 0;
				idx2 = -1;
				cnt2 = 0;
				etype = 0;
				idx1 = 685;
				taid = 3;
			}
		}
		CDboTSContReward
		{
			canclnk = 101;
			cid = 100;
			desc = 66814;
			nextlnk = 254;
			rwdtbl = 66801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "101;5;";
			usetbl = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 66808;
			gtype = 2;
			oklnk = 2;
			area = 66801;
			goal = 66804;
			sort = 66805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 66802;
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
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iidx1 = 685;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 684;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 66807;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
	}
}

