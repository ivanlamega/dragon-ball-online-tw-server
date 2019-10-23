CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 839;
	title = 83902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 83909;
				ctype = 1;
				idx = 1653108;
				taid = 2;
			}
			CDboTSActItem
			{
				iidx0 = 99006;
				stype0 = 1;
				taid = 3;
				type = 0;
			}
			CDboTSActRegQInfo
			{
				cont = 83908;
				gtype = 2;
				area = 83901;
				goal = 83904;
				grade = 132203;
				rwd = 100;
				sort = 83905;
				stype = 2;
				taid = 1;
				title = 83902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 83907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1653108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 37;
				minlvl = 29;
			}
			CDboTSCheckClrQst
			{
				and = "838;";
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
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 83908;
			gtype = 2;
			oklnk = 2;
			area = 83901;
			goal = 83904;
			sort = 83905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 83902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 83914;
			nextlnk = 254;
			rwdtbl = 83901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1653107;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActItem
			{
				iidx0 = 99006;
				stype0 = 1;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckItem
			{
				icnt = 1;
				iidx = 99006;
			}
		}
	}
}

