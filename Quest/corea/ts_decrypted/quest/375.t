CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 375;
	title = 37502;

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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 37507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4211101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 28;
				minlvl = 20;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 37508;
			gtype = 4;
			oklnk = 2;
			area = 37501;
			goal = 37504;
			sort = 37505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 37502;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 37509;
				ctype = 1;
				idx = 4211101;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 4511108;
				cnt0 = 6;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
			CDboTSActRegQInfo
			{
				cont = 37508;
				m1fx = "4361.000000";
				area = 37501;
				goal = 37504;
				m0fz = "293.000000";
				m0widx = 6;
				m1fy = "0.000000";
				m1ttip = 37516;
				sort = 37505;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-3444.000000";
				grade = 132203;
				m0fx = "525.000000";
				m0ttip = 37515;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 37502;
				gtype = 4;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 37514;
			nextlnk = 101;
			rwdtbl = 37501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4211101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
	}
}

