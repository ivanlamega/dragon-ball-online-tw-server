CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 331;
	title = 33102;

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
				cnt1 = 15;
				eitype = 0;
				idx0 = 5612101;
				cnt0 = 15;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = 5613101;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 33108;
			gtype = 2;
			oklnk = 2;
			area = 33101;
			goal = 33104;
			sort = 33105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 33102;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 33114;
			nextlnk = 101;
			rwdtbl = 33101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511602;
			}
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
			stdiag = 33107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511602;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 26;
				minlvl = 18;
			}
			CDboTSCheckClrQst
			{
				and = "330;";
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
				conv = 33109;
				ctype = 1;
				idx = 4511602;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 33108;
				m1fx = "4201.000000";
				area = 33101;
				goal = 33104;
				m0fz = "-1598.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 33116;
				sort = 33105;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-1599.000000";
				grade = 132203;
				m0fx = "4171.000000";
				m0ttip = 33115;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 33102;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 0;
				idx0 = 5612101;
				cnt0 = 10;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 5613101;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
	}
}

