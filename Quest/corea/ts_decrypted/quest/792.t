CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 792;
	title = 79202;

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
				conv = 79209;
				ctype = 1;
				idx = 3173201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 79208;
				gtype = 1;
				area = 79201;
				goal = 79204;
				grade = 132203;
				rwd = 100;
				sort = 79205;
				stype = 2;
				taid = 1;
				title = 79202;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 79214;
			nextlnk = 254;
			rwdtbl = 79201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3032104;
			}
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
			cont = 79208;
			gtype = 1;
			oklnk = 2;
			area = 79201;
			goal = 79204;
			sort = 79205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 79202;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 79207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3173201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 35;
				minlvl = 27;
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
	}
}

