CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 653;
	title = 65302;

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
				cont = 65308;
				gtype = 1;
				area = 65301;
				goal = 65304;
				grade = 132203;
				rwd = 100;
				sort = 65305;
				stype = 2;
				taid = 1;
				title = 65302;
			}
			CDboTSActNPCConv
			{
				conv = 65309;
				ctype = 1;
				idx = 3032103;
				taid = 2;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 65308;
			gtype = 1;
			oklnk = 2;
			area = 65301;
			goal = 65304;
			sort = 65305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 65302;
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
			desc = 65314;
			nextlnk = 254;
			rwdtbl = 65301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 65307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3032103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
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

