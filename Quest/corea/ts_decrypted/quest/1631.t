CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1631;
	title = 163102;

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
			cont = 163108;
			gtype = 2;
			oklnk = 2;
			area = 163101;
			goal = 163104;
			sort = 163105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 163102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 163114;
			nextlnk = 101;
			rwdtbl = 163101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3242103;
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
			stdiag = 163107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3242103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1630;";
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
				conv = 163109;
				ctype = 1;
				idx = 3242103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 163108;
				gtype = 2;
				area = 163101;
				goal = 163104;
				m0fz = "357.000000";
				m0widx = 1;
				sort = 163105;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "-2058.000000";
				m0ttip = 163115;
				rwd = 100;
				taid = 1;
				title = 163102;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 7212103;
				cnt0 = 15;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
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

