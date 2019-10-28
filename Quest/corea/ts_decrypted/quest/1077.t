CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1077;
	title = 107702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActPCConv
			{
				taid = 1;
				tblidx = 107718;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 5;

			CDboTSColRgn
			{
				widx = 1;
				x2 = "3709.000000";
				z3 = "2307.000000";
				cct = 1;
				crt = 1;
				x1 = "3716.000000";
				x3 = "3739.000000";
				z0 = "2379.000000";
				z2 = "2310.000000";
				x0 = "3742.000000";
				z1 = "2371.000000";
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
				conv = 107709;
				ctype = 1;
				idx = 4071115;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 107708;
				gtype = 1;
				area = 107701;
				goal = 107704;
				grade = 132203;
				rwd = 100;
				sort = 107705;
				stype = 2;
				taid = 1;
				title = 107702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 107707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4071115;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 107708;
			gtype = 1;
			oklnk = 2;
			area = 107701;
			goal = 107704;
			sort = 107705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 107702;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 107714;
			nextlnk = 254;
			rwdtbl = 107701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4071115;
			}
		}
	}
}

