CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1619;
	title = 161902;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 161907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4952101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 161914;
			nextlnk = 101;
			rwdtbl = 161901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4952101;
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
				conv = 161909;
				ctype = 1;
				idx = 4952101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 161908;
				m1fx = "-268.000000";
				m2fz = "-520.000000";
				m1fy = "0.000000";
				sort = 161905;
				m2widx = 10;
				grade = 132203;
				m0fx = "-391.000000";
				m0ttip = 161915;
				m1widx = 10;
				rwd = 100;
				taid = 1;
				title = 161902;
				gtype = 4;
				area = 161901;
				goal = 161904;
				m0fz = "-611.000000";
				m0widx = 10;
				m1ttip = 161916;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-487.000000";
				m2fx = "-251.000000";
				m2ttip = 161917;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 0;
				idx0 = 6212112;
				cnt0 = 10;
				cnt2 = 10;
				ectype = -1;
				etype = 0;
				idx1 = 4261107;
				taid = 3;
				esctype = 0;
				idx2 = 1781104;
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
			cont = 161908;
			gtype = 4;
			oklnk = 2;
			area = 161901;
			goal = 161904;
			sort = 161905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 161902;
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

