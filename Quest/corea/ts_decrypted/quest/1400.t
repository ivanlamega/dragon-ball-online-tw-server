CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1400;
	title = 140002;

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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 140014;
			nextlnk = 101;
			rwdtbl = 140001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511606;
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
			stdiag = 140007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511606;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 140008;
			gtype = 2;
			oklnk = 2;
			area = 140001;
			goal = 140004;
			sort = 140005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 140002;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 140009;
				ctype = 1;
				idx = 4511606;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 140008;
				m1fx = "3868.000000";
				area = 140001;
				goal = 140004;
				m0fz = "4207.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 140016;
				sort = 140005;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "4175.000000";
				grade = 132203;
				m0fx = "3858.000000";
				m0ttip = 140015;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 140002;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 18;
				eitype = 0;
				idx0 = 9413101;
				cnt0 = 18;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 9413201;
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
				itype = 0;
			}
		}
	}
}

