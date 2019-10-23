CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 983;
	title = 98302;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 98307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7131119;
			}
			CDboTSCheckLvl
			{
				maxlvl = 44;
				minlvl = 36;
			}
			CDboTSCheckClrQst
			{
				and = "981;";
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
				conv = 98309;
				ctype = 1;
				idx = 7131119;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 98308;
				m1fx = "1637.000000";
				area = 98301;
				goal = 98304;
				m0fz = "584.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 98316;
				sort = 98305;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "723.000000";
				grade = 132203;
				m0fx = "1780.000000";
				m0ttip = 98315;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 98302;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 20;
				eitype = 0;
				idx0 = 7813200;
				cnt0 = 20;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 7813100;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 98308;
			gtype = 2;
			oklnk = 2;
			area = 98301;
			goal = 98304;
			sort = 98305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 98302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 98314;
			nextlnk = 101;
			rwdtbl = 98301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7131119;
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

