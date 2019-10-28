CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1432;
	title = 143202;

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
			stdiag = 143207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4071108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSCheckClrQst
			{
				and = "1431;";
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
				conv = 143209;
				ctype = 1;
				idx = 4071108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 143208;
				m1fx = "-533.000000";
				area = 143201;
				goal = 143204;
				m0fz = "958.000000";
				m0widx = 2;
				m1fy = "0.000000";
				m1ttip = 143216;
				sort = 143205;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "1046.000000";
				grade = 132203;
				m0fx = "-555.000000";
				m0ttip = 143215;
				m1widx = 2;
				rwd = 100;
				taid = 1;
				title = 143202;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 15;
				eitype = 0;
				idx0 = 6613306;
				cnt0 = 15;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 4813102;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 143208;
			gtype = 2;
			oklnk = 2;
			area = 143201;
			goal = 143204;
			sort = 143205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 143202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 143214;
			nextlnk = 101;
			rwdtbl = 143201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4071108;
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

