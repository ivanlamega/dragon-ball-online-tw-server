CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 325;
	title = 32502;

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
			stdiag = 32507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4751308;
			}
			CDboTSCheckLvl
			{
				maxlvl = 25;
				minlvl = 17;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 32508;
			gtype = 3;
			oklnk = 2;
			area = 32501;
			goal = 32504;
			sort = 32505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 32502;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 32509;
				ctype = 1;
				idx = 4751308;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 32508;
				m1fx = "4354.000000";
				area = 32501;
				goal = 32504;
				m0fz = "-1657.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 32516;
				sort = 32505;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-1531.000000";
				grade = 132203;
				m0fx = "4381.000000";
				m0ttip = 32515;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 32502;
				gtype = 3;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 1;
				idx0 = 496;
				cnt0 = 15;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 497;
				taid = 3;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 32514;
			nextlnk = 101;
			rwdtbl = 32501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511208;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iidx1 = 497;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 496;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
	}
}

