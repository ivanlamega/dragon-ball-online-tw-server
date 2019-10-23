CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1262;
	title = 126202;

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
			cid = 5;
			elnk = 255;
			nextlnk = 100;
			prelnk = "4;";

			CDboTSActItem
			{
				iidx0 = 99045;
				stype0 = 1;
				taid = 1;
				type = 0;
			}
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 5;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckItem
			{
				icnt = 1;
				iidx = 99045;
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
			stdiag = 126207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1431102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 51;
				minlvl = 43;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 126208;
			gtype = 3;
			oklnk = 2;
			area = 126201;
			goal = 126204;
			sort = 126205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 126202;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 126209;
				ctype = 1;
				idx = 1431102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 126208;
				m1fx = "2177.000000";
				area = 126201;
				goal = 126204;
				m0fz = "3172.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 126216;
				sort = 126205;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "3157.000000";
				grade = 132203;
				m0fx = "2162.000000";
				m0ttip = 126215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 126202;
				gtype = 3;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 0;
				idx0 = 1711106;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 1711107;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 126214;
			nextlnk = 101;
			rwdtbl = 126201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1431102;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

