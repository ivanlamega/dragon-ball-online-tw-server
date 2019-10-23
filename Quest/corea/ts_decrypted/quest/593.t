CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 593;
	title = 59302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 59307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 10;
			}
			CDboTSClickNPC
			{
				npcidx = 6413106;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 59308;
			gtype = 2;
			oklnk = 2;
			area = 59301;
			goal = 59304;
			sort = 59305;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 59302;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 59314;
			nextlnk = 101;
			rwdtbl = 59301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6413106;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 1199;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 1198;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 59308;
				m1fx = "6108.000000";
				area = 59301;
				goal = 59304;
				m0fz = "-3072.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 59316;
				sort = 59305;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-3109.000000";
				grade = 132203;
				m0fx = "6025.000000";
				m0ttip = 59315;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 59302;
				gtype = 2;
			}
			CDboTSActNPCConv
			{
				conv = 59309;
				ctype = 1;
				idx = 6413106;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 1;
				idx0 = 1198;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 1199;
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
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iidx1 = 1199;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 1198;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 59307;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

