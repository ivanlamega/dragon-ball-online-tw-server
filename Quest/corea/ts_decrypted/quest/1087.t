CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1087;
	title = 108702;

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
				conv = 108709;
				ctype = 1;
				idx = 1655201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 108708;
				gtype = 2;
				area = 108701;
				goal = 108704;
				grade = 132203;
				rwd = 100;
				sort = 108705;
				stype = 2;
				taid = 1;
				title = 108702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 108707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1655201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
			cont = 108708;
			gtype = 2;
			oklnk = 2;
			area = 108701;
			goal = 108704;
			sort = 108705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 108702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 108714;
			nextlnk = 254;
			rwdtbl = 108701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1655301;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

