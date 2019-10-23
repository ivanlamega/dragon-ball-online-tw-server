CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1290;
	title = 129002;

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
		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActItem
			{
				iidx0 = 99039;
				stype0 = 1;
				taid = 1;
				type = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActItem
			{
				iidx0 = 99039;
				stype0 = 1;
				taid = 2;
				type = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 5;
				idx0 = -1;
				cnt0 = 0;
				ectype = -1;
				etype = 1;
				qtidx = -1;
				taid = 1;
				esctype = 0;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 129014;
			nextlnk = 101;
			rwdtbl = 129001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2611102;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
			cont = 129008;
			gtype = 2;
			oklnk = 2;
			area = 129001;
			goal = 129004;
			sort = 129005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 129002;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 129007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2611102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 5;
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
				conv = 129009;
				ctype = 1;
				idx = 2611102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 129008;
				m1fx = "2337.000000";
				m2fz = "3631.000000";
				m1fy = "0.000000";
				sort = 129005;
				m2widx = 1;
				grade = 132203;
				m0fx = "2213.000000";
				m0ttip = 129015;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 129002;
				gtype = 2;
				area = 129001;
				goal = 129004;
				m0fz = "4290.000000";
				m0widx = 1;
				m1ttip = 129015;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "4450.000000";
				m2fx = "1997.000000";
				m2ttip = 129015;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 5;
				idx0 = 176;
				cnt0 = 8;
				ectype = -1;
				etype = 0;
				qtidx = 129030;
				taid = 3;
				esctype = 0;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 253;
			prelnk = "0;";

			CDboTSActItem
			{
				iidx0 = 99039;
				stype0 = 1;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

