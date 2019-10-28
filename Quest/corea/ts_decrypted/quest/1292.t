CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1292;
	title = 129202;

	CNtlTSGroup
	{
		gid = 0;

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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 129207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1752103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 129209;
				ctype = 1;
				idx = 1752103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 129208;
				gtype = 1;
				area = 129201;
				goal = 129204;
				grade = 132203;
				rwd = 100;
				sort = 129205;
				stype = 1;
				taid = 1;
				title = 129202;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 129214;
			nextlnk = 254;
			rwdtbl = 129201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickObject
			{
				objidx = "672;";
				widx = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 129208;
			gtype = 1;
			oklnk = 2;
			area = 129201;
			goal = 129204;
			sort = 129205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 129202;
		}
	}
}

