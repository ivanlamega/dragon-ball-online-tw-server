CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1063;
	title = 106302;

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
				conv = 106309;
				ctype = 1;
				idx = 4072101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 106308;
				gtype = 1;
				area = 106301;
				goal = 106304;
				grade = 132203;
				rwd = 100;
				sort = 106305;
				stype = 2;
				taid = 1;
				title = 106302;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 106314;
			nextlnk = 254;
			rwdtbl = 106301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4071115;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 106308;
			gtype = 1;
			oklnk = 2;
			area = 106301;
			goal = 106304;
			sort = 106305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 106302;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 106307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4072101;
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
	}
}

