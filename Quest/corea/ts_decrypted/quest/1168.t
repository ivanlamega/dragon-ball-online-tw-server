CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1168;
	title = 116802;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 116808;
				gtype = 0;
				area = 116801;
				goal = 116804;
				grade = 132203;
				rwd = 100;
				sort = 116805;
				stype = 2;
				taid = 1;
				title = 116802;
			}
			CDboTSActNPCConv
			{
				conv = 116809;
				ctype = 1;
				idx = 3031208;
				taid = 2;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 116808;
			gtype = 1;
			oklnk = 2;
			area = 116801;
			goal = 116804;
			sort = 116805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 116802;
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
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 116814;
			nextlnk = 254;
			rwdtbl = 116801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3242111;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 116807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
			CDboTSCheckClrQst
			{
				and = "1167;";
			}
			CDboTSClickNPC
			{
				npcidx = 3031208;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

