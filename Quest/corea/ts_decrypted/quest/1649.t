CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1649;
	title = 164902;

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
				conv = 164909;
				ctype = 1;
				idx = 6312110;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 164908;
				gtype = 0;
				area = 164901;
				goal = 164904;
				grade = 132203;
				rwd = 100;
				sort = 164905;
				stype = 2;
				taid = 1;
				title = 164902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 164907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6312110;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1648;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 164908;
			gtype = 0;
			oklnk = 2;
			area = 164901;
			goal = 164904;
			sort = 164905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 164902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 164914;
			nextlnk = 254;
			rwdtbl = 164901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7135201;
			}
		}
	}
}

