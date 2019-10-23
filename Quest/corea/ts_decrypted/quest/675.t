CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 675;
	title = 67502;

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
			stdiag = 67507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3332203;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 31;
				minlvl = 23;
			}
			CDboTSCheckClrQst
			{
				and = "674;";
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
				conv = 67509;
				ctype = 1;
				idx = 3332203;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 67508;
				m1fx = "6659.799805";
				m2fz = "1484.099976";
				m1fy = "0.000000";
				sort = 67505;
				m2widx = 1;
				grade = 132203;
				m0fx = "6659.799805";
				m0ttip = 67515;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 67502;
				gtype = 2;
				area = 67501;
				goal = 67504;
				m0fz = "1484.099976";
				m0widx = 1;
				m1ttip = 67516;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "1484.099976";
				m2fx = "6659.799805";
				m2ttip = 67517;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 1;
				idx0 = 536;
				cnt0 = 8;
				cnt2 = 8;
				ectype = -1;
				etype = 0;
				idx1 = 537;
				taid = 3;
				esctype = 0;
				idx2 = 538;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 67514;
			nextlnk = 101;
			rwdtbl = 67501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3173106;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 67508;
			gtype = 2;
			oklnk = 2;
			area = 67501;
			goal = 67504;
			sort = 67505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 67502;
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

		CDboTSContStart
		{
			cid = 0;
			stdiag = 67507;
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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt2 = 255;
				iprob2 = "1.000000";
				icnt1 = 255;
				iidx0 = 536;
				iidx2 = 538;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
				icnt0 = 255;
				iidx1 = 537;
				iprob0 = "1.000000";
			}
		}
	}
}

