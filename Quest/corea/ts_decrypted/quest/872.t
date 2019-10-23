CNtlTSTrigger
{
	sm = 1;
	sq = 0;
	rq = 1;
	tid = 872;
	title = 87202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 87209;
				ctype = 1;
				idx = 1653108;
				taid = 2;
			}
			CDboTSActItem
			{
				iidx0 = 99064;
				stype0 = 1;
				taid = 1;
				type = 0;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 6;
				tidx0 = 1;
				ectype = -1;
				etype = 0;
				iidx0 = -1;
				it0 = 87220;
				taid = 3;
				widx0 = 3;
				dt0 = 87221;
				esctype = 0;
				otype0 = 7;
			}
			CDboTSActRegQInfo
			{
				cont = 87208;
				gtype = 1;
				area = 87201;
				goal = 87204;
				grade = 132203;
				rwd = 100;
				sort = 87205;
				stype = 1;
				taid = 1;
				title = 87202;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSRcvSvrEvt
			{
				id = 188;
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
				itype = 6;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;100;";

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
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContReward
		{
			canclnk = 101;
			cid = 100;
			desc = 87214;
			nextlnk = 101;
			rwdtbl = 87201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 87208;
			gtype = 1;
			oklnk = 2;
			area = 87201;
			goal = 87204;
			sort = 87205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 87202;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 87207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1653108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 38;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "839;";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 87207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActItem
			{
				iidx0 = 99064;
				stype0 = 1;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
	}
}

