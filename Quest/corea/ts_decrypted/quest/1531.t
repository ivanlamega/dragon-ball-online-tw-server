CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1531;
	title = 153102;

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
				eitype = 6;
				esctype = 0;
				ectype = -1;
				etype = 1;
				taid = 1;
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
			cont = 153108;
			gtype = 2;
			oklnk = 2;
			area = 153101;
			goal = 153104;
			sort = 153105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 153102;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 153109;
				ctype = 1;
				idx = 4372106;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 153108;
				gtype = 2;
				area = 153101;
				goal = 153104;
				grade = 132203;
				rwd = 100;
				sort = 153105;
				stype = 2;
				taid = 1;
				title = 153102;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 6;
				tidx0 = 807;
				ectype = -1;
				etype = 0;
				iidx0 = -1;
				it0 = 153120;
				taid = 3;
				widx0 = 1;
				dt0 = 153121;
				esctype = 0;
				otype0 = 7;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 153114;
			nextlnk = 101;
			rwdtbl = 153101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372106;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;1;0;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 153107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4372106;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
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
				itype = 6;
			}
		}
	}
}

