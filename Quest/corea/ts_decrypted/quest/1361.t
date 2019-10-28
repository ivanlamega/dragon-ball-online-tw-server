CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1361;
	title = 136102;

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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 136108;
			gtype = 2;
			oklnk = 2;
			area = 136101;
			goal = 136104;
			sort = 136105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 136102;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 136109;
				ctype = 1;
				idx = 4372206;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 136108;
				m1fx = "1458.000000";
				m2fz = "4706.000000";
				m1fy = "0.000000";
				sort = 136105;
				m2widx = 1;
				grade = 132203;
				m0fx = "1367.000000";
				m0ttip = 136115;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 136102;
				gtype = 2;
				area = 136101;
				goal = 136104;
				m0fz = "5154.000000";
				m0widx = 1;
				m1ttip = 136116;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "5031.000000";
				m2fx = "1868.000000";
				m2ttip = 136117;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 0;
				idx0 = 7111300;
				cnt0 = 10;
				cnt2 = 10;
				ectype = -1;
				etype = 0;
				idx1 = 7112300;
				taid = 3;
				esctype = 0;
				idx2 = 7113400;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 136114;
			nextlnk = 101;
			rwdtbl = 136101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372206;
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
			stdiag = 136107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4372206;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1360;";
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

