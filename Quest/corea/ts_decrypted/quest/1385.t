CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1385;
	title = 138502;

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
				conv = 138509;
				ctype = 1;
				idx = 1351111;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 138508;
				gtype = 1;
				area = 138501;
				goal = 138504;
				grade = 132203;
				rwd = 100;
				sort = 138505;
				stype = 1;
				taid = 1;
				title = 138502;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 138507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1351111;
			}
			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
			}
			CDboTSCheckClrQst
			{
				and = "1384;";
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
			cont = 138508;
			gtype = 1;
			oklnk = 2;
			area = 138501;
			goal = 138504;
			sort = 138505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 138502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 138514;
			nextlnk = 254;
			rwdtbl = 138501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1353102;
			}
		}
	}
}

